contract WhiteList {

  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }
}