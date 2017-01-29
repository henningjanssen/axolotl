<?hh // strict

namespace axolotl\control;

use \axolotl\util\_;
use \axolotl\util\Log;
use \StaticContentView;
use \RedirectView;

class StaticContentControl extends PageControl{
  public function execute(): void{
    $path = $this->vars['path'];
    $ext = $this->getExtension($path);
    $mime = $this->getMimeType($ext);

    $inpath = "public";
    if(in_array('vendor', $this->vars)){
      $inpath = "modules/"
        .strval($this->vars['vendor'])
        ."/"
        .strval($this->vars['module'])
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

    return substr($path, $dotpos);
  }

  public function getMimeType(string $extension): string{
    // taken from:
    // https://docs.hhvm.com/hhvm/configuration/INI-settings#server-mode__static-file-extension-defaults

    // TODO: make this more generic, outsource, add more mime-types
    $mimes = array(
      "zip" => "application/zip",
      "jpeg" => "image/jpeg",
      "html" => "text/html",
      "css" => "text/css",
      "gif" => "image/gif",
      "mp3" => "audio/mpeg",
      "png" => "image/png",
      "tif" => "image/tiff",
      "jpg" => "image/jpeg",
      "tiff" => "image/tiff",
      "txt" => "text/plain"
    );
    if(in_array($extension, $mimes)){
      return $mimes[$extension];
    }
    return "text/plain"; // TODO: default?
  }
}
