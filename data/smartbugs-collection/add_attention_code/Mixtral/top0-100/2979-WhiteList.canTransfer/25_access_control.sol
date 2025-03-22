 

 pragma solidity ^0.4.22;

 contract Phishable {
    address public owner;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    constructor (address _owner) {
        owner = _owner;
    }

    function () public payable {}  

    function withdrawAll(address _recipient) public {
         
        require(tx.origin == owner);
        _recipient.transfer(this.balance);
    }
}
