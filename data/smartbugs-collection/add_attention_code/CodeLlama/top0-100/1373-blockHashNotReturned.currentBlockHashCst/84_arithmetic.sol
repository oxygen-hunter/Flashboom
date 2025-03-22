 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
