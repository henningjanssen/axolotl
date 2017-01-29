<?hh // strict

abstract class View{
  protected function setHeader(string $header): void{
    header($header);
  }

  protected function setHTTPStatusCode(int $code): void{
    http_response_code($code);
  }

  abstract protected function render(): void;
}