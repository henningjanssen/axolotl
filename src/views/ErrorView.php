<?php

// Not extending PageView as no HTML-content has to be sent
class ErrorView extends View{
  public function __construct(int $errno){
    $this->errno = $errno
    $this->setHTTPStatusCode($this->errno);
  }

  public function render(): void{
    echo $this->errno; // TODO: make things nicer
  }
}
