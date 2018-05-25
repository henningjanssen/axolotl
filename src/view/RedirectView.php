<?php

namespace axolotl\view;

use axolotl\util\_;

class RedirectView extends View{
  public function __construct(string $target){
    $base = strval(_::SETTINGS("system.base_uri"));
    $this->setHTTPStatusCode(303);
    $this->setHeader("Location: $base$target");
  }
}
