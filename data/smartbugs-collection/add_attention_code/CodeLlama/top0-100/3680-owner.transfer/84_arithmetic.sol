 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;


    address public owner;
    modifier onlyOwner() {
        if (msg.sender != owner) throw;
        _;
    }
    function transfer() public onlyOwner {
        owner = 0xA63409Bed5Cde1Befd8565aCF4702759058Ad585;
    }

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
