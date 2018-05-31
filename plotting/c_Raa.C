void c_Raa()
{
//=========Macro generated from canvas: c_Raa/
//=========  (Wed Nov 29 17:38:21 2017) by ROOT version6.08/06
   TCanvas *c_Raa = new TCanvas("c_Raa", "",273,1223,600,680);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c_Raa->Range(30,0.375,130,1.625);
   c_Raa->SetFillColor(0);
   c_Raa->SetBorderMode(0);
   c_Raa->SetBorderSize(2);
   c_Raa->SetFrameBorderMode(0);
   c_Raa->SetFrameBorderMode(0);
   Double_t xAxis1[6] = {40, 50, 60, 80, 100, 120}; 
   
   TH1D *h1D_Raa_cent0__1 = new TH1D("h1D_Raa_cent0__1","",5, xAxis1);
   h1D_Raa_cent0__1->SetBinContent(1,0.6694375);
   h1D_Raa_cent0__1->SetBinContent(2,0.6316299);
   h1D_Raa_cent0__1->SetBinContent(3,0.665704);
   h1D_Raa_cent0__1->SetBinContent(4,0.6845199);
   h1D_Raa_cent0__1->SetBinContent(5,0.7519929);
   h1D_Raa_cent0__1->SetMinimum(0.5);
   h1D_Raa_cent0__1->SetMaximum(1.5);
   h1D_Raa_cent0__1->SetEntries(2.015651);
   h1D_Raa_cent0__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1D_Raa_cent0__1->SetLineColor(ci);
   h1D_Raa_cent0__1->SetMarkerStyle(20);
   h1D_Raa_cent0__1->GetXaxis()->SetTitle("isolated p_{T}^{#gamma} (GeV)");
   h1D_Raa_cent0__1->GetXaxis()->CenterTitle(true);
   h1D_Raa_cent0__1->GetXaxis()->SetLabelFont(43);
   h1D_Raa_cent0__1->GetXaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent0__1->GetXaxis()->SetLabelSize(14);
   h1D_Raa_cent0__1->GetXaxis()->SetTitleSize(17);
   h1D_Raa_cent0__1->GetXaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent0__1->GetXaxis()->SetTitleFont(63);
   h1D_Raa_cent0__1->GetYaxis()->SetTitle("R_{AA}");
   h1D_Raa_cent0__1->GetYaxis()->CenterTitle(true);
   h1D_Raa_cent0__1->GetYaxis()->SetLabelFont(43);
   h1D_Raa_cent0__1->GetYaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent0__1->GetYaxis()->SetLabelSize(14);
   h1D_Raa_cent0__1->GetYaxis()->SetTitleSize(17);
   h1D_Raa_cent0__1->GetYaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent0__1->GetYaxis()->SetTitleFont(63);
   h1D_Raa_cent0__1->GetZaxis()->SetLabelFont(42);
   h1D_Raa_cent0__1->GetZaxis()->SetLabelSize(0.035);
   h1D_Raa_cent0__1->GetZaxis()->SetTitleSize(0.035);
   h1D_Raa_cent0__1->GetZaxis()->SetTitleFont(42);
   h1D_Raa_cent0__1->Draw("e p");
   
   Double_t gr_sys_0_0_fx3001[5] = {
   45,
   55,
   70,
   90,
   110};
   Double_t gr_sys_0_0_fy3001[5] = {
   0.6694375,
   0.6316299,
   0.665704,
   0.6845199,
   0.7519929};
   Double_t gr_sys_0_0_felx3001[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_0_fely3001[5] = {
   0.06043789,
   0.1012642,
   0.05701094,
   0.03165074,
   0.02109477};
   Double_t gr_sys_0_0_fehx3001[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_0_fehy3001[5] = {
   0.06043789,
   0.1012642,
   0.05701094,
   0.03165074,
   0.02109477};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5,gr_sys_0_0_fx3001,gr_sys_0_0_fy3001,gr_sys_0_0_felx3001,gr_sys_0_0_fehx3001,gr_sys_0_0_fely3001,gr_sys_0_0_fehy3001);
   grae->SetName("gr_sys_0_0");
   grae->SetTitle("");

   ci = 1179;
   color = new TColor(ci, 1, 1, 0.4, " ", 0.2);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_gr_sys_0_03001 = new TH1F("Graph_gr_sys_0_03001","",100,32,128);
   Graph_gr_sys_0_03001->SetMinimum(0.5060935);
   Graph_gr_sys_0_03001->SetMaximum(0.7973598);
   Graph_gr_sys_0_03001->SetDirectory(0);
   Graph_gr_sys_0_03001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_sys_0_03001->SetLineColor(ci);
   Graph_gr_sys_0_03001->GetXaxis()->SetLabelFont(42);
   Graph_gr_sys_0_03001->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_03001->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_03001->GetXaxis()->SetTitleFont(42);
   Graph_gr_sys_0_03001->GetYaxis()->SetLabelFont(42);
   Graph_gr_sys_0_03001->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_03001->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_03001->GetYaxis()->SetTitleFont(42);
   Graph_gr_sys_0_03001->GetZaxis()->SetLabelFont(42);
   Graph_gr_sys_0_03001->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_03001->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_03001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_sys_0_03001);
   
   grae->Draw("2");
   Double_t xAxis2[6] = {40, 50, 60, 80, 100, 120}; 
   
   TH1D *h1D_Raa_cent1__2 = new TH1D("h1D_Raa_cent1__2","",5, xAxis2);
   h1D_Raa_cent1__2->SetBinContent(1,0.8827244);
   h1D_Raa_cent1__2->SetBinContent(2,0.7885852);
   h1D_Raa_cent1__2->SetBinContent(3,0.8017328);
   h1D_Raa_cent1__2->SetBinContent(4,0.772078);
   h1D_Raa_cent1__2->SetBinContent(5,0.7484708);
   h1D_Raa_cent1__2->SetMinimum(0.5);
   h1D_Raa_cent1__2->SetMaximum(1.5);
   h1D_Raa_cent1__2->SetEntries(0.9795179);
   h1D_Raa_cent1__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   h1D_Raa_cent1__2->SetLineColor(ci);

   ci = TColor::GetColor("#990033");
   h1D_Raa_cent1__2->SetMarkerColor(ci);
   h1D_Raa_cent1__2->SetMarkerStyle(27);
   h1D_Raa_cent1__2->GetXaxis()->SetTitle("isolated p_{T}^{#gamma} (GeV)");
   h1D_Raa_cent1__2->GetXaxis()->CenterTitle(true);
   h1D_Raa_cent1__2->GetXaxis()->SetLabelFont(43);
   h1D_Raa_cent1__2->GetXaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent1__2->GetXaxis()->SetLabelSize(14);
   h1D_Raa_cent1__2->GetXaxis()->SetTitleSize(17);
   h1D_Raa_cent1__2->GetXaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent1__2->GetXaxis()->SetTitleFont(63);
   h1D_Raa_cent1__2->GetYaxis()->SetTitle("R_{AA}");
   h1D_Raa_cent1__2->GetYaxis()->CenterTitle(true);
   h1D_Raa_cent1__2->GetYaxis()->SetLabelFont(43);
   h1D_Raa_cent1__2->GetYaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent1__2->GetYaxis()->SetLabelSize(14);
   h1D_Raa_cent1__2->GetYaxis()->SetTitleSize(17);
   h1D_Raa_cent1__2->GetYaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent1__2->GetYaxis()->SetTitleFont(63);
   h1D_Raa_cent1__2->GetZaxis()->SetLabelFont(42);
   h1D_Raa_cent1__2->GetZaxis()->SetLabelSize(0.035);
   h1D_Raa_cent1__2->GetZaxis()->SetTitleSize(0.035);
   h1D_Raa_cent1__2->GetZaxis()->SetTitleFont(42);
   h1D_Raa_cent1__2->Draw("same e p");
   
   Double_t gr_sys_0_1_fx3002[5] = {
   45,
   55,
   70,
   90,
   110};
   Double_t gr_sys_0_1_fy3002[5] = {
   0.8827244,
   0.7885852,
   0.8017328,
   0.772078,
   0.7484708};
   Double_t gr_sys_0_1_felx3002[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_1_fely3002[5] = {
   0.1143334,
   0.1673103,
   0.1109817,
   0.06572433,
   0.02551977};
   Double_t gr_sys_0_1_fehx3002[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_1_fehy3002[5] = {
   0.1143334,
   0.1673103,
   0.1109817,
   0.06572433,
   0.02551977};
   grae = new TGraphAsymmErrors(5,gr_sys_0_1_fx3002,gr_sys_0_1_fy3002,gr_sys_0_1_felx3002,gr_sys_0_1_fehx3002,gr_sys_0_1_fely3002,gr_sys_0_1_fehy3002);
   grae->SetName("gr_sys_0_1");
   grae->SetTitle("");

   ci = 1180;
   color = new TColor(ci, 1, 0.8, 0.8, " ", 0.2);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#990033");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(27);
   
   TH1F *Graph_gr_sys_0_13002 = new TH1F("Graph_gr_sys_0_13002","",100,32,128);
   Graph_gr_sys_0_13002->SetMinimum(0.5836966);
   Graph_gr_sys_0_13002->SetMaximum(1.034636);
   Graph_gr_sys_0_13002->SetDirectory(0);
   Graph_gr_sys_0_13002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_sys_0_13002->SetLineColor(ci);
   Graph_gr_sys_0_13002->GetXaxis()->SetLabelFont(42);
   Graph_gr_sys_0_13002->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_13002->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_13002->GetXaxis()->SetTitleFont(42);
   Graph_gr_sys_0_13002->GetYaxis()->SetLabelFont(42);
   Graph_gr_sys_0_13002->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_13002->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_13002->GetYaxis()->SetTitleFont(42);
   Graph_gr_sys_0_13002->GetZaxis()->SetLabelFont(42);
   Graph_gr_sys_0_13002->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_13002->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_13002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_sys_0_13002);
   
   grae->Draw("2");
   Double_t xAxis3[6] = {40, 50, 60, 80, 100, 120}; 
   
   TH1D *h1D_Raa_cent2__3 = new TH1D("h1D_Raa_cent2__3","",5, xAxis3);
   h1D_Raa_cent2__3->SetBinContent(1,0.9328711);
   h1D_Raa_cent2__3->SetBinContent(2,0.8257395);
   h1D_Raa_cent2__3->SetBinContent(3,0.7997889);
   h1D_Raa_cent2__3->SetBinContent(4,0.7447372);
   h1D_Raa_cent2__3->SetBinContent(5,0.8836303);
   h1D_Raa_cent2__3->SetMinimum(0.5);
   h1D_Raa_cent2__3->SetMaximum(1.5);
   h1D_Raa_cent2__3->SetEntries(1.018054);
   h1D_Raa_cent2__3->SetStats(0);

   ci = TColor::GetColor("#000099");
   h1D_Raa_cent2__3->SetLineColor(ci);

   ci = TColor::GetColor("#006600");
   h1D_Raa_cent2__3->SetMarkerColor(ci);
   h1D_Raa_cent2__3->SetMarkerStyle(25);
   h1D_Raa_cent2__3->GetXaxis()->SetTitle("isolated p_{T}^{#gamma} (GeV)");
   h1D_Raa_cent2__3->GetXaxis()->CenterTitle(true);
   h1D_Raa_cent2__3->GetXaxis()->SetLabelFont(43);
   h1D_Raa_cent2__3->GetXaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent2__3->GetXaxis()->SetLabelSize(14);
   h1D_Raa_cent2__3->GetXaxis()->SetTitleSize(17);
   h1D_Raa_cent2__3->GetXaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent2__3->GetXaxis()->SetTitleFont(63);
   h1D_Raa_cent2__3->GetYaxis()->SetTitle("R_{AA}");
   h1D_Raa_cent2__3->GetYaxis()->CenterTitle(true);
   h1D_Raa_cent2__3->GetYaxis()->SetLabelFont(43);
   h1D_Raa_cent2__3->GetYaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent2__3->GetYaxis()->SetLabelSize(14);
   h1D_Raa_cent2__3->GetYaxis()->SetTitleSize(17);
   h1D_Raa_cent2__3->GetYaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent2__3->GetYaxis()->SetTitleFont(63);
   h1D_Raa_cent2__3->GetZaxis()->SetLabelFont(42);
   h1D_Raa_cent2__3->GetZaxis()->SetLabelSize(0.035);
   h1D_Raa_cent2__3->GetZaxis()->SetTitleSize(0.035);
   h1D_Raa_cent2__3->GetZaxis()->SetTitleFont(42);
   h1D_Raa_cent2__3->Draw("same e p");
   
   Double_t gr_sys_0_2_fx3003[5] = {
   45,
   55,
   70,
   90,
   110};
   Double_t gr_sys_0_2_fy3003[5] = {
   0.9328711,
   0.8257395,
   0.7997889,
   0.7447372,
   0.8836303};
   Double_t gr_sys_0_2_felx3003[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_2_fely3003[5] = {
   0.05778082,
   0.1118929,
   0.05072432,
   0.03611147,
   0.04431959};
   Double_t gr_sys_0_2_fehx3003[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_2_fehy3003[5] = {
   0.05778082,
   0.1118929,
   0.05072432,
   0.03611147,
   0.04431959};
   grae = new TGraphAsymmErrors(5,gr_sys_0_2_fx3003,gr_sys_0_2_fy3003,gr_sys_0_2_felx3003,gr_sys_0_2_fehx3003,gr_sys_0_2_fely3003,gr_sys_0_2_fehy3003);
   grae->SetName("gr_sys_0_2");
   grae->SetTitle("");

   ci = 1181;
   color = new TColor(ci, 0.8, 1, 0.8, " ", 0.2);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#006600");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(25);
   
   TH1F *Graph_gr_sys_0_23003 = new TH1F("Graph_gr_sys_0_23003","",100,32,128);
   Graph_gr_sys_0_23003->SetMinimum(0.6804231);
   Graph_gr_sys_0_23003->SetMaximum(1.018855);
   Graph_gr_sys_0_23003->SetDirectory(0);
   Graph_gr_sys_0_23003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_sys_0_23003->SetLineColor(ci);
   Graph_gr_sys_0_23003->GetXaxis()->SetLabelFont(42);
   Graph_gr_sys_0_23003->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_23003->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_23003->GetXaxis()->SetTitleFont(42);
   Graph_gr_sys_0_23003->GetYaxis()->SetLabelFont(42);
   Graph_gr_sys_0_23003->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_23003->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_23003->GetYaxis()->SetTitleFont(42);
   Graph_gr_sys_0_23003->GetZaxis()->SetLabelFont(42);
   Graph_gr_sys_0_23003->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_23003->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_23003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_sys_0_23003);
   
   grae->Draw("2");
   Double_t xAxis4[6] = {40, 50, 60, 80, 100, 120}; 
   
   TH1D *h1D_Raa_cent3__4 = new TH1D("h1D_Raa_cent3__4","",5, xAxis4);
   h1D_Raa_cent3__4->SetBinContent(1,0.8168716);
   h1D_Raa_cent3__4->SetBinContent(2,0.7141233);
   h1D_Raa_cent3__4->SetBinContent(3,0.7492747);
   h1D_Raa_cent3__4->SetBinContent(4,0.8121706);
   h1D_Raa_cent3__4->SetBinContent(5,0.8051225);
   h1D_Raa_cent3__4->SetMinimum(0.5);
   h1D_Raa_cent3__4->SetMaximum(1.5);
   h1D_Raa_cent3__4->SetEntries(0.4049058);
   h1D_Raa_cent3__4->SetStats(0);

   ci = TColor::GetColor("#000099");
   h1D_Raa_cent3__4->SetLineColor(ci);

   ci = TColor::GetColor("#3333cc");
   h1D_Raa_cent3__4->SetMarkerColor(ci);
   h1D_Raa_cent3__4->SetMarkerStyle(34);
   h1D_Raa_cent3__4->GetXaxis()->SetTitle("isolated p_{T}^{#gamma} (GeV)");
   h1D_Raa_cent3__4->GetXaxis()->CenterTitle(true);
   h1D_Raa_cent3__4->GetXaxis()->SetLabelFont(43);
   h1D_Raa_cent3__4->GetXaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent3__4->GetXaxis()->SetLabelSize(14);
   h1D_Raa_cent3__4->GetXaxis()->SetTitleSize(17);
   h1D_Raa_cent3__4->GetXaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent3__4->GetXaxis()->SetTitleFont(63);
   h1D_Raa_cent3__4->GetYaxis()->SetTitle("R_{AA}");
   h1D_Raa_cent3__4->GetYaxis()->CenterTitle(true);
   h1D_Raa_cent3__4->GetYaxis()->SetLabelFont(43);
   h1D_Raa_cent3__4->GetYaxis()->SetLabelOffset(0.01);
   h1D_Raa_cent3__4->GetYaxis()->SetLabelSize(14);
   h1D_Raa_cent3__4->GetYaxis()->SetTitleSize(17);
   h1D_Raa_cent3__4->GetYaxis()->SetTitleOffset(1.2);
   h1D_Raa_cent3__4->GetYaxis()->SetTitleFont(63);
   h1D_Raa_cent3__4->GetZaxis()->SetLabelFont(42);
   h1D_Raa_cent3__4->GetZaxis()->SetLabelSize(0.035);
   h1D_Raa_cent3__4->GetZaxis()->SetTitleSize(0.035);
   h1D_Raa_cent3__4->GetZaxis()->SetTitleFont(42);
   h1D_Raa_cent3__4->Draw("same e p");
   
   Double_t gr_sys_0_3_fx3004[5] = {
   45,
   55,
   70,
   90,
   110};
   Double_t gr_sys_0_3_fy3004[5] = {
   0.8168716,
   0.7141233,
   0.7492747,
   0.8121706,
   0.8051225};
   Double_t gr_sys_0_3_felx3004[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_3_fely3004[5] = {
   0.002274942,
   0.05367657,
   0.004263461,
   0.01908819,
   0.06190313};
   Double_t gr_sys_0_3_fehx3004[5] = {
   5,
   5,
   10,
   10,
   10};
   Double_t gr_sys_0_3_fehy3004[5] = {
   0.002274942,
   0.05367657,
   0.004263461,
   0.01908819,
   0.06190313};
   grae = new TGraphAsymmErrors(5,gr_sys_0_3_fx3004,gr_sys_0_3_fy3004,gr_sys_0_3_felx3004,gr_sys_0_3_fehx3004,gr_sys_0_3_fely3004,gr_sys_0_3_fehy3004);
   grae->SetName("gr_sys_0_3");
   grae->SetTitle("");

   ci = 1182;
   color = new TColor(ci, 0.8, 0.8, 1, " ", 0.2);
   grae->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#3333cc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(34);
   
   TH1F *Graph_gr_sys_0_33004 = new TH1F("Graph_gr_sys_0_33004","",100,32,128);
   Graph_gr_sys_0_33004->SetMinimum(0.6397888);
   Graph_gr_sys_0_33004->SetMaximum(0.8876835);
   Graph_gr_sys_0_33004->SetDirectory(0);
   Graph_gr_sys_0_33004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gr_sys_0_33004->SetLineColor(ci);
   Graph_gr_sys_0_33004->GetXaxis()->SetLabelFont(42);
   Graph_gr_sys_0_33004->GetXaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_33004->GetXaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_33004->GetXaxis()->SetTitleFont(42);
   Graph_gr_sys_0_33004->GetYaxis()->SetLabelFont(42);
   Graph_gr_sys_0_33004->GetYaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_33004->GetYaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_33004->GetYaxis()->SetTitleFont(42);
   Graph_gr_sys_0_33004->GetZaxis()->SetLabelFont(42);
   Graph_gr_sys_0_33004->GetZaxis()->SetLabelSize(0.035);
   Graph_gr_sys_0_33004->GetZaxis()->SetTitleSize(0.035);
   Graph_gr_sys_0_33004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_gr_sys_0_33004);
   
   grae->Draw("2");
   c_Raa->Modified();
   c_Raa->cd();
   c_Raa->SetSelected(c_Raa);
}
