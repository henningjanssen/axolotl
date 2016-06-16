<?hh // strict

namespace axolotl\test\control;

abstract class ControlTest{
  <<Setup('test')>>
  public async function setUp(): Awaitable<void>{
    ob_start();
  }

  <<TearDown('test')>>
  public async function tearDown(): Awaitable<void>{
    ob_end_clean();
  }
}
