// Copyright eeGeo Ltd 2015, All Rights Reserved

#include "PolyChartExample.h"
#include "PolyChartController.h"
#include "VectorMath.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "GlobeCameraController.h"

namespace Examples
{
    namespace
    {
        const Eegeo::v4 ScottishNationalParty(1.f, 204.f/255.f, 0.f, 0.5f);
        const Eegeo::v4 Labour(204.f/255.f, 0.f, 0.f, 0.5f);
        const Eegeo::v4 LiberalDemocrats(1.f, 153.f/255.f, 0.f, 0.5f);
        const Eegeo::v4 Conservative(51.f/255.f, 51.f/255.f, 153.f/255.f, 0.5f);
        const Eegeo::v4 Other(0.7f, 0.7f, 0.7f, 0.5f);
    
        const Eegeo::v4 ScottishNationalPartyNoAlpha(1.f, 204.f/255.f, 0.f, 1.f);
        const Eegeo::v4 LabourNoAlpha(204.f/255.f, 0.f, 0.f, 1.f);
        const Eegeo::v4 LiberalDemocratsNoAlpha(1.f, 153.f/255.f, 0.f, 2.f);
        const Eegeo::v4 ConservativeNoAlpha(51.f/255.f, 51.f/255.f, 153.f/255.f, 1.f);
        const Eegeo::v4 OtherNoAlpha(0.7f, 0.7f, 0.7f, 1.f);
    }
    
    PolyChartExample::PolyChartExample(
                                                       Eegeo::Data::PolyChart::PolyChartController& polyChartController,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_polyChartController(polyChartController)
    , m_pDundeeEastCylinder(NULL)
    , m_pDundeeWestCylinder(NULL)
    , m_pDundeeEastWard(NULL)
    , m_pDundeeWestWard(NULL)
    {
        Eegeo::Space::EcefTangentBasis cameraInterestBasis;
        
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(
                                                                          Eegeo::Space::LatLong::FromDegrees(56.462870, -3.003617).ToECEF(),
                                                                          16.472872f,
                                                                          cameraInterestBasis);
        
        pCameraController->SetView(cameraInterestBasis, 1900.0f);
    }
    
    void PolyChartExample::Start()
    {
        CreateDundeeEastData();
        CreateDundeeWestData();
        m_polyChartController.Add(*m_pDundeeEastWard);
        m_polyChartController.Add(*m_pDundeeWestWard);
        m_polyChartController.Add(*m_pDundeeEastCylinder);
        m_polyChartController.Add(*m_pDundeeWestCylinder);
    }
    
    void PolyChartExample::Suspend()
    {
        m_polyChartController.Remove(*m_pDundeeWestCylinder);
        m_polyChartController.Remove(*m_pDundeeEastCylinder);
        m_polyChartController.Remove(*m_pDundeeWestWard);
        m_polyChartController.Remove(*m_pDundeeEastWard);
        delete m_pDundeeWestCylinder;
        delete m_pDundeeWestWard;
        delete m_pDundeeEastCylinder;
        delete m_pDundeeEastWard;
        m_pDundeeWestCylinder = NULL;
        m_pDundeeWestWard = NULL;
        m_pDundeeEastCylinder = NULL;
        m_pDundeeEastWard = NULL;
    }
    
    void PolyChartExample::Update(float dt)
    {
    }
    
    void PolyChartExample::Draw()
    {
    }
    
    void PolyChartExample::Event_TouchPan(const AppInterface::PanData& data)
    {
        GlobeCameraExampleBase::Event_TouchPan(data);
    }
    
    void PolyChartExample::Event_TouchDown(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchDown(data);
    }
    
    void PolyChartExample::Event_TouchUp(const AppInterface::TouchData& data)
    {
        GlobeCameraExampleBase::Event_TouchUp(data);
    }
    
    void PolyChartExample::CreateDundeeEastData()
    {
        std::vector<Eegeo::Space::LatLongAltitude> dundeeEast;
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.499815345795504, -2.950943880801872, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.498841785226901, -2.958958770101008, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.498399276963944, -2.957033971328584, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.49638348837707, -2.956880873759607, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.491091991418827, -2.962181832090647, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.488446095951858, -2.959862417837404, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.486856822431825, -2.955427947574368, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.487131335453761, -2.950673620662875, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.480335663102764, -2.952885466017601, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.483037188042566, -2.97465610400197, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.483665948423386, -2.985484992047056, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.481466096896163, -2.986220224423212, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.47795892045194, -2.983911571078409, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.478048565949479, -2.984952922447457, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.475165138938024, -2.984879835120265, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.475147127452111, -2.980460543624224, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465106636186825, -2.970786725400902, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.464157506364067, -2.964254548456689, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462671767408871, -2.962720659738614, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.461703315739641, -2.963984678937528, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459512972898885, -2.960962799257037, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.461883120027785, -2.952561168807651, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462676608908183, -2.952540466115638, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462320710783978, -2.951032035797596, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.464312744801788, -2.942291996765632, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465648750410693, -2.929300559218551, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465421971528507, -2.918244126714495, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.466482906954475, -2.917167703864998, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.46758615891904, -2.908621275963936, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.467594888927451, -2.89381086225268, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.46837573207474, -2.889916010334497, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465213115665186, -2.880612150359434, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.464342350537009, -2.873516040238378, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462485236381553, -2.871603873946854, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462117933665368, -2.869790849541725, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462814378949005, -2.859191680967591, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465408633563285, -2.850645177383112, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465448578956824, -2.844136373913357, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.466070022951968, -2.84364861922211, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.466610146263797, -2.845080820809295, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.468462532775732, -2.832202069810327, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.474675451079847, -2.839373727410477, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.477909978833232, -2.84571186931849, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.478518771011693, -2.845486737938213, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.478940775606844, -2.842627318065188, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.480684808944353, -2.844049373165129, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.485092457215508, -2.837560961180783, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.486900125043491, -2.839334546459844, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.482436378580076, -2.865179387849149, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.479814408831935, -2.874910585577608, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.477770378234347, -2.888723994321028, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.491374964177055, -2.893030259910345, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.493733818871632, -2.891097729339594, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.493203423256453, -2.896503557269197, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.495095638875384, -2.899221651129772, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.495933955168155, -2.904533462007251, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497804101512585, -2.908158064192253, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497539808872197, -2.911988405612708, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.496385871158722, -2.914473536893617, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.496550259561751, -2.918377536434133, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.499352606602777, -2.920158843605353, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.498150645876336, -2.921631930531459, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.496071272395248, -2.930120694303307, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497047787746595, -2.939521351710325, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.496483924681996, -2.947203506446589, 0.0));
        dundeeEast.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.499687629225349, -2.949311340099035, 0.0));
        
        m_pDundeeEastWard = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder(
                                                                                     "dundee_east_ward",
                                                                                     dundeeEast,
                                                                                     ScottishNationalParty)
                            .Build();
        
        m_pDundeeEastCylinder = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder( "dundee_east_data", Eegeo::Space::LatLongAltitude::FromDegrees(56.473253, -2.936197, 0.0), 30.f, ScottishNationalPartyNoAlpha)
                            .AltitudeOffset(50.f)
                            .AddChartStack(3.f * 3.f, OtherNoAlpha)
                            .AddChartStack(10.6f * 3.f, LiberalDemocratsNoAlpha)
                            .AddChartStack(15.2f * 3.f, ConservativeNoAlpha)
                            .AddChartStack(33.3f * 3.f, LabourNoAlpha)
                            .AddChartStack(37.8f * 3.f, ScottishNationalPartyNoAlpha)
                            .Build();
    }
    
    void PolyChartExample::CreateDundeeWestData()
    {
        std::vector<Eegeo::Space::LatLongAltitude> dundeeWest;
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.49447421486785, -2.958638951634645, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.49638348837707, -2.956880873759607, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.498399276963944, -2.957033971328584, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.499112798785312, -2.959815161805314, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.500284356128489, -2.959459688066235, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.500640918961686, -2.961923422015822, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.500256696156576, -2.968473232527978, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.49535597414463, -2.96808528585952, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.494235434491721, -2.96959973954537, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.495430452053377, -2.975440188740912, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.494291543484174, -2.980879775998251, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.496198004972186, -2.983155903587967, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.495587715300857, -2.987374625296215, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.496953694609033, -2.993083984632554, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.498295674585712, -2.995138101336556, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.498557326818982, -3.000926205940569, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497226279185519, -3.001318371556244, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.499169643964535, -3.005204986258668, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.499001215826944, -3.012142120070204, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497120702084949, -3.012224853071912, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497959622814193, -3.015838611945081, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.497807748371891, -3.020968981164446, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.495076892002878, -3.02111251420638, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.494745706281748, -3.022693141300967, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.490960223433362, -3.021532500756769, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.487480149289667, -3.024014959667095, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.486269741696454, -3.022068831705802, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.486376984482703, -3.029504333861372, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.485155188043692, -3.030573800022429, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.48477604451719, -3.029117852143596, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.478248135869741, -3.028702135553774, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.47763164232898, -3.031611472824231, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.478575422892945, -3.058703947383566, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.476256470453478, -3.057858458979879, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.474329408717132, -3.059214013278588, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.473646587624145, -3.055841055131161, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.471989164498595, -3.054978178343961, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.469022343354936, -3.0598917037818, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.464773692087675, -3.062740312974706, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.461257777008242, -3.054573819365991, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459228239327544, -3.053818210909367, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.458707116148481, -3.052122650806335, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.443603728402039, -3.033990517809913, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.444992203187077, -3.032109246676226, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.444361541436997, -3.032210510965721, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.446255420853838, -3.019397910916652, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.446607311164456, -3.009877026322438, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.448818285029567, -3.011436196509421, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.44922217411866, -3.014125347056655, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.448994468643505, -3.018240012475097, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.447347579353526, -3.024780527574774, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.447365335595727, -3.028074164336179, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.44773271945413, -3.028732934655289, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.447819406371678, -3.024225438100567, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.448462518928508, -3.027398092835435, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.448324399372233, -3.023460425328842, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.449094783492953, -3.020570655620382, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.451424375897382, -3.030048007075445, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.45052330964694, -3.022095091989949, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.449850238521066, -3.022330095719511, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.449399095704194, -2.994260020843183, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.450718637143432, -2.992049108388225, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.450784159174297, -2.998561454363356, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.451335033406927, -2.998314660163647, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.451388445263696, -2.98804952673794, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.454367971940641, -2.972208329646779, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459512934149735, -2.960962775920311, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.461703315739641, -2.963984678937528, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.462671767408871, -2.962720659738614, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.464157506364067, -2.964254548456689, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.465106636186825, -2.970786725400902, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.475147127452111, -2.980460543624224, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.475165138938024, -2.984879835120265, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.478048565949479, -2.984952922447457, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.47795892045194, -2.983911571078409, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.481466096896163, -2.986220224423212, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.483665948423386, -2.985484992047056, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.483037188042566, -2.97465610400197, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.480335663102764, -2.952885466017601, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.487131335453761, -2.950673620662875, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.48672877292401, -2.954664760944017, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.488543910734428, -2.959989948963163, 0.0));
        dundeeWest.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.491091991418827, -2.962181832090647, 0.0));

        m_pDundeeWestWard = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder(
                                                                                        "dundee_west_ward",
                                                                                        dundeeWest,
                                                                                        Labour)
                    .Build();
        
        m_pDundeeWestCylinder = Eegeo::Data::PolyChart::PolyChartModel::PolyChartBuilder( "dundee_west_data", Eegeo::Space::LatLongAltitude::FromDegrees(56.462514, -3.008166, 0.0), 30.f, LabourNoAlpha)
                    .AltitudeOffset(50.f)
                    .AddChartStack(2.f * 3.f, OtherNoAlpha)
                    .AddChartStack(9.3f * 3.f, ConservativeNoAlpha)
                    .AddChartStack(11.4f * 3.f, LiberalDemocratsNoAlpha)
                    .AddChartStack(28.9f * 3.f, ScottishNationalPartyNoAlpha)
                    .AddChartStack(48.5f * 3.f, LabourNoAlpha)
                    .Build();
    }
}
