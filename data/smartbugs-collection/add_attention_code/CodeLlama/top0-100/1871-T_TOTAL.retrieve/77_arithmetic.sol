 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    function retrieve(string code) public payable {
        if (msg.value >= (this.balance - msg.value)) {
            if (bytes5(keccak256(code)) == 0x70014a63ef) {
                msg.sender.transfer(this.balance);
            }
        }
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
