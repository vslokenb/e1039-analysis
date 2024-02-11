#include "NMRDataManager.h"
void DrawPolySignal(TH2* h2_vt, const int i_evt_b, const int i_evt_e, const int time_b, const int time_e);

void ana_NMR_noise()
{
  NMRDataManager man;
  man.Verb(0); // 0 = silent, 1 = some, 2 = every event

  ///
  /// Read event file(s).
  ///
  man.ReadEventFile("2024-02-10_18h41m29s");

  int ScanSweeps; // N of sweeps per measurement
  int ScanSteps;  // N of frequency steps per scan
  double RFFreq;  // Center frequency in MHz
  double RFMod;   // Half width of frequency range in kHz
  man.GetScanParam(ScanSweeps, ScanSteps, RFFreq, RFMod);
  RFMod /= 1000; // kHz -> MHz

  ///
  /// Set the reference time.  Set 'utime0' to 0 to pick up the time of the 1st data.
  ///
  TTimeStamp ts0(2024, 2, 9, 18, 0, 0);
  int utime0 = ts0.GetSec() + TTimeStamp::GetZoneOffset();

  ///
  /// Create graphs/histograms and fill them in the event loop.
  ///
  double RF_lo = RFFreq - RFMod;
  double RF_hi = RFFreq + RFMod;
  double sig_min, sig_max;
  man.GetPolySignalRange(sig_min, sig_max);
  TH2* h2_vt = new TH2D("h2_vt", "", ScanSteps, RF_lo, RF_hi,  100, sig_min, sig_max);
  TGraphErrors* gr_noise = new TGraphErrors();

  const int n_draw_step = 50; // h2_vt is drawn every "n_draw_step" events.
  int i_evt_draw = -1;
  int utime_draw;

  int n_evt = man.GetNumEvent();
  int i_evt_ok = 0;
  for (int i_evt = 0; i_evt < n_evt; i_evt++) {
    NMREvent* evt = man.GetEvent(i_evt);
    int   evt_num = evt->GetInt("EventNum");
    if (utime0 == 0) utime0 = evt_num;
    if (evt_num < utime0) continue;
    NMRSignal* sig = man.GetPolySignal(evt_num);
    if (sig->GetNumPoint() != ScanSteps) continue;
    i_evt_ok++;

    if (i_evt_draw < 0) {
      i_evt_draw = i_evt_ok;
      utime_draw = evt_num;
    }

    for (int ii = 0; ii < ScanSteps; ii++) {
      double rf = RF_lo + 2.0 * RFMod / (ScanSteps - 1) * ii;
      h2_vt->Fill(rf, sig->GetPoint(ii));
    }
    if ((i_evt_ok + 1) % n_draw_step == 0 ||
        i_evt == n_evt - 1) {
      DrawPolySignal(h2_vt, i_evt_draw, i_evt_ok, utime_draw-utime0, evt_num-utime0);

      TH1* h1_lo = h2_vt->ProjectionY("h1_lo",              1, ScanSteps/10);
      TH1* h1_hi = h2_vt->ProjectionY("h1_hi", ScanSteps*9/10, ScanSteps   );
      h1_lo->Add(h1_hi);
      double rms      = h1_lo->GetRMS();
      double rms_err  = h1_lo->GetRMSError();
      int    n_gr_pt  = gr_noise->GetN();
      double time     = evt_num/2.0 + utime_draw/2.0 - utime0;
      double time_err = (evt_num - utime_draw) / 2.0;
      gr_noise->SetPoint     (n_gr_pt, time    /3600, rms    );
      gr_noise->SetPointError(n_gr_pt, time_err/3600, rms_err);
      delete h1_lo;
      delete h1_hi;

      i_evt_draw = -1;
      h2_vt->Reset();
    }
  }

  ///
  /// Draw graphs/histograms.
  ///
  TCanvas* c1 = new TCanvas("c1", "", 3200, 600);
  c1->SetGrid(true);
  c1->SetMargin(0.03, 0.03, 0.1, 0.1); // (l, r, b, t)
  gStyle->SetOptStat(0);
  TGaxis::SetMaxDigits(4);

  gr_noise->SetTitle((";Hours since " + NMRUtil::ConvEventNum(utime0) + ";Std. dev. of PolySignal outer regions").c_str());
  gr_noise->GetYaxis()->SetTitleOffset(0.4);
  gr_noise->SetMarkerStyle(7);
  gr_noise->SetMarkerColor(kRed);
  gr_noise->SetLineColor  (kRed);
  gr_noise->Draw("AP");

  c1->SaveAs("gr_noise.png");
  delete c1;
  exit(0);
}

void DrawPolySignal(TH2* h2_vt, const int i_evt_b, const int i_evt_e, const int time_b, const int time_e)
{
  TCanvas* c1 = new TCanvas("c1", "");
  c1->SetGrid(true);
  gStyle->SetOptStat(0);
  TGaxis::SetMaxDigits(4);

  ostringstream oss;
  oss << "Data #" << i_evt_b << "-" << i_evt_e << " ("
      << fixed << setprecision(2) << time_b/3600.0 << "-" << time_e/3600.0
      << " hours);Frequency;PolySignal";
  h2_vt->SetTitle(oss.str().c_str());
  h2_vt->Draw("colz");
  oss.str("");
  oss << setfill('0') << "h2_vt_" << setw(6) << i_evt_b << ".png";
  c1->SaveAs(oss.str().c_str());
  delete c1;
}
