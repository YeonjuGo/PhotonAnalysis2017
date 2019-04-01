#include "TFile.h"
#include "TObject.h"
#include "TString.h"
#include "TCanvas.h"
#include "TKey.h"

#include "RooWorkspace.h"

#include "TagProbeFitter.C"

#include <iostream>
#include <stdlib.h>

// print efficiencies with cut method?
bool print_cuteff = false;

// print efficiencies with fit method?
bool print_fiteff = true;

using namespace std;

// A "simple" macro to read a ROOT file as created by the TnP fitting code, and print the canvases corresponding to the mass fits,
// as well as the final efficiency plot.
// The code is quite ugly, sorry about that... The idea was to iterate on the contents on the file to guess where are the interesting stuff.

void plot(const char *filename)
{
   TFile *f = new TFile(filename);
   TIter next(f->GetListOfKeys()); TObject *obj;
   while ((obj = next()))
   {
      obj = ((TKey*) obj)->ReadObj();
      if (TString(obj->ClassName()) == "TDirectoryFile")
      {

	string name = string(filename);
	name = name.substr(0, name.size()-5);
	system((string("mkdir ") + name).c_str());

         // first-level directory
         TDirectoryFile *tdir = dynamic_cast<TDirectoryFile*>(obj);
         tdir->cd();
         TIter next2(tdir->GetListOfKeys()); TObject *obj2;
         while ((obj2 = next2()))
         {
            obj2 = ((TKey*) obj2)->ReadObj();
            if (TString(obj2->ClassName()) == "TDirectoryFile")
            {
               // second level: one for each series of fits (typically pt, eta, 1bin, ...)
               TDirectoryFile *tdir2 = dynamic_cast<TDirectoryFile*>(obj2);
               tdir2->cd();
               TString dir2name(tdir2->GetName());
	       /*
	       string name = string(filename);
	       name = name.substr(0, name.size()-5);
	       system((string("mkdir ") + name).c_str());*/
               string cmd = string("mkdir ") + string(name) + "/" + string(tdir2->GetName());
               system(cmd.c_str());
               TIter next3(tdir2->GetListOfKeys()); TObject *obj3;
               while ((obj3 = next3()))
               {
                  obj3 = ((TKey*) obj3)->ReadObj();
                  if (TString(obj3->ClassName()) == "TDirectoryFile" && TString(obj3->GetName()).Contains("bin"))
                  {
                     // we are in a directory with mass fits. Print the canvases with these fits.
                     TDirectoryFile *tdir3 = dynamic_cast<TDirectoryFile*>(obj3);
                     tdir3->cd();

		     cout << "in dir with mass fits" << endl;

                     RooWorkspace *myws = (RooWorkspace*) gDirectory->Get("w");
                     if (myws)
                     {
                        TagProbeFitter tnpf;
                        tnpf.setBinsForMassPlots(50);
                        tnpf.saveFitPlot(myws,dir2name + "/" + TString(obj3->GetName()),dir2name + "/" + TString(obj3->GetName()) + "_pulls");
			cout << "rooworkspace" << endl;
                     }
                     else
                     {
		       cout << "going to fit_canvas" << endl;
		       TCanvas *canv = (TCanvas*) gDirectory->Get("fit_canvas");
		       if (!canv) continue;
		       canv->SaveAs(name + "/" + dir2name + "/" + TString(obj3->GetName()) + ".pdf");
		       canv->SaveAs(name + "/" + dir2name + "/" + TString(obj3->GetName()) + ".png");
		       canv = (TCanvas*) gDirectory->Get("pull_canvas");
		       if (!canv) continue;
		       canv->SaveAs(name + "/" + dir2name + "/" + TString(obj3->GetName()) + "_pulls.pdf");
		       canv->SaveAs(name + "/" + dir2name + "/" + TString(obj3->GetName()) + "_pulls.png");
                     }
                  }
                  if ((print_fiteff && TString(obj3->GetTitle()) == "fit_eff_plots") || (print_cuteff && TString(obj3->GetTitle()) == "cnt_eff_plots"))
                  {

		    cout << "in dir with eff plots" << endl;
                     // we are in a directory with efficiency plots. Print these efficiency plots.
                     TDirectoryFile *tdir3 = dynamic_cast<TDirectoryFile*>(obj3);
                     tdir3->cd();
                     TIter next4(tdir3->GetListOfKeys()); TObject *obj4;
                     while ((obj4 = next4()))
                     {
                        obj4 = ((TKey*) obj4)->ReadObj();

			string obj4Name = string(obj4->GetName());
			string plot = string("_PLOT");
			std::size_t found = obj4Name.find(plot);

			cout << "found = " << found << endl;

			if(found>0)
			  //if (((TObjString*) (TString(obj4->GetName()).Tokenize("_"))->At(1))->String() == "PLOT") // in this case we have a 1D efficiency plot, which is what we want
                        {
                           cout << obj4->GetName() << endl;
                           TCanvas *canv = (TCanvas*) obj4;
                           TString prefix = (TString(obj3->GetTitle()) == "fit_eff_plots") ? "fit_" : "cut_";
                           canv->SaveAs(name + "/" + dir2name + "/" + prefix + TString(obj4->GetName()) + ".pdf");
                           canv->SaveAs(name + "/" + dir2name + "/" + prefix + TString(obj4->GetName()) + ".png");
                        }
                     }
                  }
               }
            }
         }
      }
   }
}
