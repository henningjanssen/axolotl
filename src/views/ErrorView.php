<?php

namespace \axolotl\view;

// Not extending PageView as no HTML-content has to be sent
class ErrorView extends PageView{
  public function __construct(int $errno){
    parent::construct("Error")
    $this->errno = $errno
    $this->setHTTPStatusCode($this->errno);
    $this->setTemplateFile("error.html");
    $this->setVars(array('errno' => $errno));
  }
}
