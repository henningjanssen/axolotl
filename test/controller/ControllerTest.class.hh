<?hh // strict

namespace axolotl\test\controller;

abstract class ControllerTest{
  <<Setup('test')>>
  public async function setUp(): Awaitable<void>{
    ob_start();
  }

  <<TearDown('test')>>
  public async function tearDown(): Awaitable<void>{
    ob_end_clean();
  }
}
