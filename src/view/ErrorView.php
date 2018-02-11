<?php

namespace axolotl\view;

// Not extending PageView as no HTML-content has to be sent
class ErrorView extends PageView{
  public function __construct(int $errno){
    parent::construct("error.html", "Error");
    $this->errno = $errno;
    $this->setHTTPStatusCode($this->errno);
    $this->setVars(array('errno' => $errno));
  }
}
