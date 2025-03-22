 

pragma solidity ^0.4.24;

contract MyContract {

    address owner;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    function MyContract() public {
        owner = msg.sender;
    }

    function sendTo(address receiver, uint amount) public {
         
        require(tx.origin == owner);
        receiver.transfer(amount);
    }

}
