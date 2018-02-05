<?php

namespace axolotl\control;

use \AboutView;

class AboutControl extends LoggedInPageControl{
  public function execute(): void{
    (new AboutView())->render();
  }
}
