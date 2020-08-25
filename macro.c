/*
Questa macro permette di graficare tramite software root i dati raccolti dal programma 
elaborando il file report.txt
Assicurarsi che il file sia nella stessa directory di questa macro

Le opzioni disponibili sono: 
graphS() per la stampa dell'andamento dei suscettibili
graphI() per la stampa dell'andamento degli infetti
graphR() per la stampa dell'andamento dei guariti
graphD() per la stampa dell'andamento dei morti
graphEpidemic() per la stampa contemporanea dei dati su un unico grafico
graphAll() per tutte le opzioni precedenti
 */

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//functions

void graphS() {

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(1);

auto c1 = new TCanvas();
TGraph *graphS = new TGraph ("report.txt", "%lg %lg %*lg %*lg %*lg");
graphS->SetTitle("Susceptibles; Time (days); ");
graphS->SetMinimum(0);
c1->SetTitle("Susceptibles");
graphS->Draw();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void graphI() {

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(1);

auto c2 = new TCanvas();
TGraph *graphI = new TGraph ("report.txt", "%lg %*lg %lg %*lg %*lg");
graphI->SetTitle("Infects; Time (days); ");
graphI->SetMinimum(0);
c2-> SetTitle("Infects");
graphI->Draw();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void graphR() {

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(1);

auto c3 = new TCanvas();
TGraph *graphR = new TGraph ("report.txt", "%lg %*lg %*lg %lg %*lg");
graphR->SetTitle("Recovered; Time (days); ");
graphR->SetMinimum(0);
c3->SetTitle("Recovered");
graphR->Draw();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void graphD() {

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(1);

auto c4 = new TCanvas();
TGraph *graphD = new TGraph ("report.txt", "%lg %*lg %*lg %*lg %lg");
graphD->SetTitle("Dead; Time (days); ");
graphD->SetMinimum(0);
c4->SetTitle("Dead");
graphD->Draw();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void graphEpidemic() {

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(1);

auto c1 = new TCanvas();


//lettura dati da file -> il file di lettura deve chiamarsi report.txt ed essere nella stessa directory
TGraph *graphS = new TGraph ("report.txt", "%lg %lg %*lg %*lg %*lg");
TGraph *graphI = new TGraph ("report.txt", "%lg %*lg %lg %*lg %*lg");
TGraph *graphR = new TGraph ("report.txt", "%lg %*lg %*lg %lg %*lg");
TGraph *graphD = new TGraph ("report.txt", "%lg %*lg %*lg %*lg %lg");

graphS->SetMinimum(0);

//impostazioni grafiche
graphS->SetTitle("Epidemic; Time (days); ");
graphS->SetLineColor(1);
graphI->SetLineColor(2);
graphR->SetLineColor(67);
graphD->SetLineColor(9);


//legenda
auto legend = new TLegend(0.7, 0.4, 0.9, 0.6);
TLegendEntry *leS = legend->AddEntry("graphS", "Susceptibles", "l");
TLegendEntry *leI = legend->AddEntry("graphI", "Infects", "l");
TLegendEntry *leR = legend->AddEntry("graphR", "Recovered", "l");
TLegendEntry *leD = legend->AddEntry("graphD", "Dead", "l");

leS->SetTextColor(1);
leI->SetTextColor(2);
leR->SetTextColor(67);
leD->SetTextColor(9);

leS->SetLineColor(1);
leI->SetLineColor(2);
leR->SetLineColor(67);
leD->SetLineColor(9);


//rappresentazione
graphS->Draw();
graphI->Draw("same");
graphR->Draw("same");
graphD->Draw("same");
legend->Draw("same");

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void graphAll() {
    graphS();
    graphI();
    graphR();
    graphD();
    graphEpidemic();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
