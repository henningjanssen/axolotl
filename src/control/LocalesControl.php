<?php

namespace axolotl\control;

use axolotl\view\ErrorView;
use axolotl\view\StaticContentView;

class LocalesControl extends PageControl{
  public function execute(): void{
    $lang = $this->vars['lang'];
    $ns = $this->vars['ns'];

    $path = __DIR__.'/../../';
    if($ns === "axolotl"){
      $path .= '/public';
    }
    else{
      list($vendor, $module) = explode('__', $ns);
      $path .= "/modules/$vendor/$module";
    }
    $path .= "/locale/$lang/translation.json";

    if(!file_exists($path)){
      (new ErrorView(404))->render();
      return;
    }
    (new StaticContentView(file_get_contents($path), 'application/json'))
      ->render();
  }
}
