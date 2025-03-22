 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function hashLoop(uint numTimes, bytes32 dataToHash) public returns (bytes32){
        for(uint i = 0 ; i < numTimes ; i++){
            dataToHash = keccak256(abi.encodePacked(dataToHash));
        }
        return dataToHash;
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
