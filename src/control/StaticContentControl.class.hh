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

    $fullpath = realpath(__DIR__."/../../public/$path");
    if(!file_exists($fullpath)){
      (new RedirectView("/error/404"))->render();
      return;
    }

    $cont = file_get_contents(__DIR__."/../../public/$path");
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
