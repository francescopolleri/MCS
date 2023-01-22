
void MLE(){
	gROOT->SetStyle("ATLAS");
	gStyle->SetOptStat(0);
	auto *rnd = new TRandom3(123456789);
	auto *tL_h = new TH1D("tL_h",
						  ";#hat{#tau} = #frac{1}{N} #sum_{i} x_{i} ;Entries", 65, 0, 0);
	double theta = 1.062;
	double x, tau_hat, expsum, tau_sum = 0;
	unsigned N = 50;
	unsigned mc_exp = 1000;
	for (unsigned i=0; i<mc_exp; i++) {
		expsum = 0;
		for (unsigned j=0; j<N; j++) {
			x = -TMath::Log(1 - rnd->Rndm()) / theta;
			expsum += x;
		}
		tau_hat = expsum / N;
		tL_h->Fill(tau_hat);
		tau_sum += pow(tau_hat - theta, 2);
	}
	double s = sqrt(tau_sum / (mc_exp - 1));
	tL_h->Draw("E0");
	std::cout << "MLE theory/exp/s = "
			  << sqrt(theta*theta / N) << "/"
			  << tL_h->GetStdDev() << "/"
			  << s  << std::endl;
}
