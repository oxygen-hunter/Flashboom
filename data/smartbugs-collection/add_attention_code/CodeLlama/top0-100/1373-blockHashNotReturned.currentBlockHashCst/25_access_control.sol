 

 pragma solidity ^0.4.22;

 contract Phishable {
    address public owner;


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
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
