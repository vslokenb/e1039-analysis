R__LOAD_LIBRARY(RecoData2024)

void AnaEventTree(const char* dir_data_base="data/ana")
{
  TChain* tree = new TChain("tree");
  void* dirp = gSystem->OpenDirectory(dir_data_base);
  while (const char* dir_name = gSystem->GetDirEntry(dirp)) {
    string file_name = (string)dir_data_base + "/" + dir_name + "/out/output.root";
    if (gSystem->AccessPathName(file_name.c_str())) continue;
    tree->Add(file_name.c_str());
  }
  gSystem->FreeDirectory(dirp);

  AnaDimuon::AnalyzeTree(tree);
  
  exit(0);
}
