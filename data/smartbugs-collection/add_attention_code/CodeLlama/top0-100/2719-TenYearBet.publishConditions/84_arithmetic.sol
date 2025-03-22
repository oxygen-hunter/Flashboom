 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;



    bytes32 public betHash = 0xc299ba54b8c29945c3a7c120bab74def2245da75162b51b1ab3b6faec6e78589;
    string public betConditions;

    function publishConditions(string _betConditions) public {
        if (keccak256(_betConditions) == betHash) {
            betConditions = _betConditions;
        }
    }


    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
