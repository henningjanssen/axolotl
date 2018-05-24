<?php

namespace axolotl\view;

use axolotl\util\_;

class RedirectView extends PageView{
  public function __construct(string $target){
    parent::__construct("", "Redirecting");
    $base = strval(_::SETTINGS("system.base_uri"));
    $this->setHTTPStatusCode(303);
    $this->setHeader("Location: $base$target");
  }
}
