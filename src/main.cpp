#include "./vdf_parser.hpp"
#include <cstdlib>
#include <format>
#include <fstream>
#include <string>
#include <tinyxml2.h>

using namespace tinyxml2;

std::string paths[35] = {
    "Resolutions/1920x1080/SequenceController",
    "Resolutions/1920x1080/ToolTip",
    "Resolutions/1920x1080/Craftbot",
    "Resolutions/1920x1080/BG",
    "Editor",
    "Language/English",
    "Resolutions/1920x1080/Logbook/Photo",
    "Resolutions/1920x1080/Beacon",
    "Resolutions/1920x1080",
    "Resolutions/1920x1080/Icons",
    "Resolutions/1920x1080/ChallengeMode",
    "NodeIcons",
    "Resolutions/1920x1080/Dressbot",
    "Resolutions/1920x1080/CharacterCustomization",
    "Resolutions/1920x1080/Inventory",
    "Resolutions/1920x1080/Keybinds",
    "Resolutions/1920x1080/Lift",
    "Resolutions/1920x1080/LightController",
    "Resolutions/1920x1080/Logbook",
    "Resolutions/1920x1080/Hud",
    "Resolutions/1920x1080/LogicGate",
    "Resolutions/1920x1080/Quest",
    "Resolutions/1920x1080/MainMenu",
    "Handbook",
    "Resolutions/1920x1080/PickupDisplay",
    "Resolutions/1920x1080/CreativeMode",
    "Resolutions/1920x1080/PopUp",
    "Resolutions/1920x1080/Seat",
    "Resolutions/1920x1080/Tutorial",
    "Fonts",
    "AssetIcons",
    "Resolutions/1920x1080/BackgroundImages",
    "Resolutions/1920x1080/CharacterSpawner",
    "Resolutions/1920x1080/PlayerSpawner",
    "Resolutions/1920x1080/QuestMarker",
};
std::string customRes[52] = {
    "EditorTemplates.xml",
    "TutorialBgBottom.xml",
    "LogicGateSkin.xml",
    "ItemColorLine.xml",
    "CustomizationIconMap.xml",
    "KeybindsSkin.xml",
    "Fonts.xml",
    "IconsLampSpritesheet.xml",
    "EditorSkin.xml",
    "BG.xml",
    "SequenceControllerRotation.xml",
    "IconMap.xml",
    "BeaconIconMap.xml",
    "BeaconSkin.xml",
    "BlurryBackgrounds.xml",
    "Skin.xml",
    "BlurrySkin.xml",
    "ButtonsLarge.xml",
    "Craftbot.xml",
    "OutfitUnlock.xml",
    "VictoryBanner.xml",
    "ContainerSlots.xml",
    "CraftbotQueue.xml",
    "DressbotSkins.xml",
    "Effects.xml",
    "HideoutTradeItemMap.xml",
    "Templates.xml",
    "IconsLarge.xml",
    "Inventory.xml",
    "ItemTypeMap.xml",
    "Lift.xml",
    "LogicGateDescriptionDots.xml",
    "Logbook.xml",
    "Lift_Templates.xml",
    "LogicGateDescriptionLamps.xml",
    "LogbookItemMap.xml",
    "Logbook_Templates.xml",
    "SeatLevels.xml",
    "WaypointIconMap.xml",
    "ToolTip.xml",
    "LogicGateIcons.xml",
    "ScrapMekTemplate.xml",
    "MainMenu.xml",
    "PickgroundBarSkin.xml",
    "PopUp.xml",
    "ToolIconMap.xml",
    "QuestpinsSkin.xml",
    "SteerAngles.xml",
    "SkinLocalized.xml",
    "TutorialBgMain.xml",
    "ScrapMekSkin.xml",
    "Rotations.xml",
};

int main() {
  std::ifstream file("/tmp/sm-gui-editor/le_user_settings.xml");
  if (file)
    return 0;
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

  XMLElement *val = settings.NewElement("Value");
  val->SetText(std::format("{}", smMediaPath).c_str());
  customPathsList->InsertEndChild(val);

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

  res->InsertFirstChild(customResList);
  res->InsertFirstChild(customPathsList);

  settings.SaveFile("le_user_settings.xml");

  return 0;
}
