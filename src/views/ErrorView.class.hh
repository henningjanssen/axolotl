<?hh // strict

// Not extending PageView as no HTML-content has to be sent
class ErrorView extends View{
  public function __construct(private int $errno){
    $this->setHTTPStatusCode($this->errno);
  }

  public function render(){
    echo $this->errno; // TODO: make things nicer
  }
}
