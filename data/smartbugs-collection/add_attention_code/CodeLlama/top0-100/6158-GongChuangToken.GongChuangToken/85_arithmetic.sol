 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxOneFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;

    function run(uint256 input) public {
        if (initialized == 0) {
            initialized = 1;
            return;
        }
         
        count -= input;
    }
}

contract BaseToken {
    uint8 public decimals  = 18;
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
}

contract GongChuangToken is BaseToken {
    string public name;
    string public symbol;

    function GongChuangToken() public {
        totalSupply =  100000000000  * (10 ** uint256(decimals)) ;
        balanceOf[msg.sender] = totalSupply;
        name = 'GongChuangToken';
        symbol = 'GCT';
    }
}
