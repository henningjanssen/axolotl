<?php

namespace axolotl\control;

use axolotl\view\AboutView;

class AboutControl extends LoggedInPageControl{
  public function execute(): void{
    (new AboutView())->render();
  }
}
