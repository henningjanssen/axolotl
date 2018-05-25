<?php

namespace axolotl\view;

use axolotl\util\_;

// Not extending PageView as no HTML-content has to be sent
class StaticContentView extends View{
  public function __construct(
    string $content, string $mimetype
  ){
    $this->content = $content;
    $this->mimetype = $mimetype;
    $this->setHeader("Content-Type: ".$this->mimetype);
  }

  public function render(): void{
    echo $this->content;
  }
}
