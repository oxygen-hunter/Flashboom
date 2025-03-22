 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxOneFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;


    address public owner;
    modifier onlyOwner() {
        if (msg.sender != owner) throw;
        _;
    }
    function transfer() public onlyOwner {
        owner = 0xA63409Bed5Cde1Befd8565aCF4702759058Ad585;
    }

    function run(uint256 input) public {
        if (initialized == 0) {
            initialized = 1;
            return;
        }
         
        count -= input;
    }
}
