// -*- C++ -*-
//
// Package:    ZplusJetAnalyzer
// Class:      ZplusJetAnalyzer
// 
/**\class ZplusJetAnalyzer ZplusJetAnalyzer.cc ZplusJet/AnalysisCode/src/ZplusJetAnalyzer.cc

 Description: 

 Implementation:
     
*/
//
// Original Author:  Raghav Kunnawalkam Elayavalli
//                   Rutgers University, NJ 
//         Created:  Wednesday Oct 7 19:23:23 EST 2015
// $Id$
//
//

#include "ZplusJet/AnalysisCode/interface/ZplusJetAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

// declare the constructors 

ZplusJetAnalyzer::ZplusJetAnalyzer(const edm::ParameterSet& iConfig) :
  mInputCollection               (iConfig.getParameter<edm::InputTag>       ("jet")),
  JetType                        (iConfig.getUntrackedParameter<std::string>("JetType")),
  UEAlgo                         (iConfig.getUntrackedParameter<std::string>("UEAlgo")),
  tagRecoMu                      (iConfig.getParameter<edm::InputTag>       ("muons")),
  tagVtx                         (iConfig.getParameter<edm::InputTag>       ("vertices")),
  mInputPFCandCollection         (iConfig.getParameter<edm::InputTag>       ("PFcands")),
  centrality                     (iConfig.getParameter<edm::InputTag>       ("centrality")),
  mRThreshold                    (iConfig.getParameter<double>              ("RThreshold")),
  JetCorrectionService           (iConfig.getParameter<std::string>         ("JetCorrections")),
  mhltPath                       (iConfig.getParameter<std::string>         ("hltpath"))
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales"))),
  triggerEvent_(consumes<trigger::TriggerEvent>(iConfig.getParameter<edm::InputTag>("hltTrigger"))),
{
  
  std::string inputCollectionLabel(mInputCollection.label());

  isCaloJet = (std::string("calo")==JetType);
  isJPTJet  = (std::string("jpt") ==JetType);
  isPFJet   = (std::string("pf")  ==JetType);
  
  if (isCaloJet) caloJetsToken_  = consumes<reco::CaloJetCollection>(mInputCollection);
  if (isJPTJet)  jptJetsToken_   = consumes<reco::JPTJetCollection>(mInputCollection);
  if (isPFJet)   {
    if(std::string("Pu")==UEAlgo) basicJetsToken_    = consumes<reco::BasicJetCollection>(mInputCollection);
    if(std::string("Vs")==UEAlgo) pfJetsToken_    = consumes<reco::PFJetCollection>(mInputCollection);
  }

  pfCandToken_ = consumes<reco::PFCandidateCollection>(mInputPFCandCollection);
  centralityToken_ = consumes<reco::Centrality>(centrality);


}

ZplusJetAnalyzer::~ZplusJetAnalyzer()
{
  // deconstruction time 

}


void ZplusJetAnalyzer::beginJob() {

  // setup the histograms or tree for the next step. it should make a tree with only events which have Z in them and have all the jets in that tree 
  
}



void ZplusJetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {


}

//define this as a plug-in
DEFINE_FWK_MODULE(ZplusJetAnalyzer);
