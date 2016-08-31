void countratepi0_roughly(TFile *f, const char *histoname){

	TH2F *histo = (TH2F*)f->Get(Form("%s",histoname));
	TH1F *scalers = (TH1F*)f->Get("SumScalers0to1095");
	TH1D *histo_px=(TH1D*)histo->ProjectionX("histo_px");
	histo_px->GetXaxis()->SetRangeUser(40,250);

	TF1 *overall= new TF1("overall", "gaus(0)+pol3(3)",50,250);
	//overall->SetParLimits(0,3000,10000);
	overall->SetParLimits(1,105,155);
	overall->SetParLimits(2,5,15);
	histo_px->Fit("overall","R");

	TF1 *signal = new TF1("signal","gaus",0,250);
	signal->FixParameter(0,overall->GetParameter(0));
	signal->FixParameter(1,overall->GetParameter(1));
	signal->FixParameter(2,overall->GetParameter(2));
	signal->SetLineColor(kBlue);


	TF1 *background = new TF1("background","pol3",50,250);
	background->FixParameter(0,overall->GetParameter(3));
	background->FixParameter(1,overall->GetParameter(4));
	background->FixParameter(2,overall->GetParameter(5));
	background->FixParameter(3,overall->GetParameter(6));
	background->SetLineColor(kGreen);

	signal->Draw("same");
	background->Draw("same");
	cout << "Peak Integral : " << signal->Integral(0,250) << endl;
	cout << "File time in h : " << scalers->GetBinContent(192)/(1e06*60*60) << endl;
	cout << "Integral per h : " << signal->Integral(0,250)/(scalers->GetBinContent(192)/(1e06*60*60)) << endl;
}
