<?hh // partial
// We need the partial mode for the use of dilab/resumable.php

namespace axolotl\control;

use \axolotl\util\_;
use \UploadView;

use \Dilab\Network\SimpleRequest;
use \Dilab\Network\SimpleResponse;
use \Dilab\Resumable;

class UploadControl extends LoggedInPageControl{
  public function execute(): void{
    /*if(strval(_::SERVER('REQUEST_METHOD')) === 'GET'){
      (new UploadView())->render();
      return;
    }*/
    \axolotl\util\Log::debug("UploadControl", strval(_::SERVER('REQUEST_METHOD')), 0);
    \axolotl\util\Log::debug("UploadControl", $this->vars["name"], 0);

    //assume it is POST otherwise.
    //library unfortunately handles the output. this is against my design
    //but I think I cannot do much about it
    $request = new SimpleRequest();
    $response = new SimpleResponse();
    $resumable = new Resumable($request, $response);
    $resumable->tempFolder = realpath(__DIR__.'/../../tmp');
    $resumable->uploadFolder = realpath(__DIR__.'/../../uploads');
    $resumable->process();
  }
}
