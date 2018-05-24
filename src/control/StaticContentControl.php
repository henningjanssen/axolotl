<?php

namespace axolotl\control;

use \axolotl\entities\Module;
use \axolotl\util\_;
use \axolotl\util\Log;
use \axolotl\view\StaticContentView;
use \axolotl\view\RedirectView;

class StaticContentControl extends PageControl{
  public function execute(): void{
    $path = $this->vars['path'];
    $ext = $this->getExtension($path);
    $mime = $this->getMimeType($ext);

    $inpath = "public";
    if(array_key_exists('vendor', $this->vars)){
      $module = Module::getByName($this->vars['vendor'], $this->vars['module']);
      $inpath = "modules/"
        .$module->getPath()
        ."/static";
    }
    $fullpath = realpath(__DIR__."/../../$inpath/$path");
    if(!file_exists($fullpath)){
      (new RedirectView("/error/404"))->render();
      return;
    }

    // disallow hidden files to be displayed
    $splitpath = explode("/", $path);
    foreach($splitpath as $p){
      if($p[0] == "."){
        (new RedirectView("/error/403"))->render();
        return;
      }
    }

    // TODO: allow wildcards (or even regex) and stuff
    $locked = _::SETTINGS("static_lock", array());
    if(in_array($path, $locked)){
      (new RedirectView("/error/403"))->render();
    }

    $cont = file_get_contents($fullpath);
    (new StaticContentView($cont, $mime))->render();
  }

  public function getExtension(string $path): string{
    $dotpos = strrpos($path, ".");
    if($dotpos === FALSE){
      return "";
    }

    $slashpos = strrpos($path, "/");
    if($dotpos < $slashpos){
      return "";
    }

    return substr($path, $dotpos+1);
  }

  public function getMimeType(string $extension): string{
    // taken from:
    // https://docs.hhvm.com/hhvm/configuration/INI-settings#server-mode__static-file-extension-defaults

    // TODO: make this more generic, outsource, add more mime-types
    $mimes = array(
      "css" => "text/css",
      "html" => "text/html",
      "gif" => "image/gif",
      "jpeg" => "image/jpeg",
      "jpg" => "image/jpeg",
      "js" => "application/javascript",
      "map" => "application/json",
      "mp3" => "audio/mpeg",
      "png" => "image/png",
      "tif" => "image/tiff",
      "tiff" => "image/tiff",
      "txt" => "text/plain",
      "zip" => "application/zip"
    );
    if(array_key_exists($extension, $mimes)){
      return $mimes[$extension];
    }
    return "text/plain"; // TODO: default?
  }
}
