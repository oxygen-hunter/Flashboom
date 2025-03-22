 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    uint public c;
    
    function pay() payable public {
        require(msg.value==0.0001 ether);
        c = c+1;
        if(c==2) {
            msg.sender.transfer(this.balance);
            c = 0;
        }
    }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
