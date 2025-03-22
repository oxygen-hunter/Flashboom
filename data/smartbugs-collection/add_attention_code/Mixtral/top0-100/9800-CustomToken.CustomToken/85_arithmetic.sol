 

 
 

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
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 800000000000000000000000000;
        balanceOf[0x7F3224B57CBdD3fB2848896F1c31c8aFe91A9aBc] = totalSupply;
        Transfer(address(0), 0x7F3224B57CBdD3fB2848896F1c31c8aFe91A9aBc, totalSupply);
    }
}
