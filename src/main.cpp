#include "./vdf_parser.hpp"
#include <cstdlib>
#include <format>
#include <fstream>
#include <string>
#include <tinyxml2.h>

using namespace tinyxml2;

std::string paths[31] = {".",
                         "Editor",
                         "Fonts",
                         "Resolutions/1920x1080",
                         "Resolutions/1920x1080/BackgroundImages",
                         "Resolutions/1920x1080/Beacon",
                         "Resolutions/1920x1080/BG",
                         "Resolutions/1920x1080/ChallengeMode",
                         "Resolutions/1920x1080/CharacterCustomization",
                         "Resolutions/1920x1080/Craftbot",
                         "Resolutions/1920x1080/CreativeMode",
                         "Resolutions/1920x1080/Dressbot",
                         "Resolutions/1920x1080/Hud",
                         "Resolutions/1920x1080/Icons",
                         "Resolutions/1920x1080/Inventory",
                         "Resolutions/1920x1080/Keybinds",
                         "Resolutions/1920x1080/Lift",
                         "Resolutions/1920x1080/LightController",
                         "Resolutions/1920x1080/Logbook",
                         "Resolutions/1920x1080/Logbook/Photo",
                         "Resolutions/1920x1080/LogicGate",
                         "Resolutions/1920x1080/MainMenu",
                         "Resolutions/1920x1080/PopUp",
                         "Resolutions/1920x1080/Quest",
                         "Resolutions/1920x1080/QuestMarker",
                         "Resolutions/1920x1080/Seat",
                         "Resolutions/1920x1080/SequenceController",
                         "Resolutions/1920x1080/ToolTip",
                         "Resolutions/1920x1080/Tutorial",
                         "Language/English",
                         "ParticleEditorGui"};
std::string customRes[46] = {"ScrapMekTemplate.xml",
                             "ScrapMekSkin.xml",
                             "Rotations.xml",
                             "EditorSkin.xml",
                             "EditorTemplates.xml",
                             "Templates.xml",
                             "SkinLocalized.xml",
                             "Skin.xml",
                             "ContainerSlots.xml",
                             "ButtonsLarge.xml",
                             "BlurrySkin.xml",
                             "BlurryBackgrounds.xml",
                             "BeaconIconMap.xml",
                             "BeaconSkin.xml",
                             "BG.xml",
                             "OutfitUnlock.xml",
                             "VictoryBanner.xml",
                             "Craftbot.xml",
                             "CraftbotQueue.xml",
                             "DressbotSkins.xml",
                             "Inventory.xml",
                             "ItemColorLine.xml",
                             "ItemTypeMap.xml",
                             "KeybindsSkin.xml",
                             "Lift.xml",
                             "Lift_Templates.xml",
                             "IconsLampSpritesheet.xml",
                             "Logbook.xml",
                             "Logbook_Templates.xml",
                             "LogbookItemMap.xml",
                             "WaypointIconMap.xml",
                             "LogicGateDescriptionDots.xml",
                             "LogicGateDescriptionLamps.xml",
                             "LogicGateIcons.xml",
                             "LogicGateSkin.xml",
                             "MainMenu.xml",
                             "PopUp.xml",
                             "QuestpinsSkin.xml",
                             "SeatLevels.xml",
                             "SteerAngles.xml",
                             "SequenceControllerRotation.xml",
                             "ToolTip.xml",
                             "TutorialBgBottom.xml",
                             "TutorialBgMain.xml",
                             "Fonts.xml",
                             "PolygonalSkin.xml"};

int main() {
  auto libraryPath = std::format("{}/Steam/steamapps/libraryfolders.vdf",
                                 getenv("XDG_DATA_HOME"));
  std::ifstream libraryFile(libraryPath);
  auto library = tyti::vdf::read(libraryFile);

  std::string libContainingSm = "";

  for (const auto &k : library.childs) {
    if (libContainingSm != "")
      break;
    for (const auto &app : k.second->childs["apps"]->attribs) {
      if (app.first != "387990")
        continue;

      libContainingSm = k.second->attribs["path"];
      break;
    }
  }

  std::string smMediaPath = std::format(
      "{}/steamapps/common/Scrap Mechanic/Data/Gui", libContainingSm);

  XMLDocument settings;
  XMLDeclaration *declaration = settings.NewDeclaration();
  XMLNode *pRoot = settings.NewElement("Settings");
  XMLElement *res = settings.NewElement("Resources");
  settings.InsertFirstChild(pRoot);
  settings.InsertFirstChild(declaration);
  pRoot->InsertFirstChild(res);

  XMLElement *customPathsList = settings.NewElement("AdditionalPath.List");
  XMLElement *customResList = settings.NewElement("AdditionalResource.List");

  for (const auto &path : paths) {
    XMLElement *val = settings.NewElement("Value");
    val->SetText(std::format("{}/{}", smMediaPath, path).c_str());
    customPathsList->InsertEndChild(val);
  }

  for (const auto &res : customRes) {
    XMLElement *val = settings.NewElement("Value");
    val->SetText(res.c_str());
    customResList->InsertEndChild(val);
  }

  res->InsertFirstChild(customPathsList);
  res->InsertFirstChild(customResList);

  settings.SaveFile("le_user_settings.xml");

  return 0;
}
