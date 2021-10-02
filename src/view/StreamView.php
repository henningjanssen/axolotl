<?php

namespace axolotl\view;

use axolotl\util\_;

// Not extending PageView as no HTML-content has to be sent
class StreamView extends View{
  public function __construct(
    $stream, string $filename, $forceDownload = true,
    $contentType = "application/octet-stream", int $initialOffset = 0,
    $flush = true
  ){
    $this->stream = $stream;
    $this->initialOffset = $initialOffset;
    $this->flush = $flush;
    $contentDisp = $forceDownload ?'attachment' :'inline';
    $this->setHeader("Content-Disposition: $contentDisp; filename=\"$filename\"");
    $this->setHeader("Content-Type: $contentType");
  }

  public function render(): void{
    $offset = $this->initialOffset;
    if($this->flush){
      while(true){
        $cont = stream_get_contents($this->stream, 102400, $offset);
        $offset = -1;
        if($cont === false){
          break;
        }
        echo $cont;
        ob_flush();
      }
    }
    else{
      echo stream_get_contents($this->stream);
    }
  }
}
