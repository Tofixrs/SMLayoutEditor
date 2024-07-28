inputs: {
  pkgs,
  stdenv,
  ...
}: let
  resources = ./resources.xml;
in
  stdenv.mkDerivation {
    pname = "MyGuiTools";
    version = "3.4.3";

    src = inputs.mygui;

    nativeBuildInputs = with pkgs; [cmake pkg-config];
    buildInputs = with pkgs; [SDL2 SDL2_image libtiff libwebp freetype libGL libGLU zlib];

    cmakeFlags = [
      "-DMYGUI_BUILD_TOOLS=ON"
      "-DMYGUI_BUILD_DEMOS=OFF"
      "-DMYGUI_BUILD_PLUGINS=OFF"
      "-DMYGUI_RENDERSYSTEM=7"
      "-DMYGUI_INSTALL_TOOLS=TRUE"
    ];

    patches = [
      ../../../patches/font_cache.patch
      ../../../patches/blurry_subskin.patch
      ../../../patches/xdg_config_for_settings.patch
    ];

    postInstall = ''
      cp ${resources} $out/share/MYGUI/resources.xml
    '';
  }
