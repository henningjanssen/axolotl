<?php

use axolotl\util\_;

// Not extending PageView as no HTML-content has to be sent
class UploadView extends View{
  public function __construct(
    bool $get = true
  ){
    if($get){
      $this->setHTTPStatusCode(200);
      return;
    }
  }

  public function render(): void{}
}
