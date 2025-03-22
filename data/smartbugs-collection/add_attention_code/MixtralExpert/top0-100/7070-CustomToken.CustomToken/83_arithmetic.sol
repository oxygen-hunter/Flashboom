 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxMultiFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;

    function init() public {
        initialized = 1;
    }

    function run(uint256 input) {
        if (initialized == 0) {
            return;
        }
         
        count -= input;
    }
}

contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 600000000000000000000000000;
        name = 'PrajnaParamitaCloud';
        symbol = 'PRMI';
        decimals = 18;
        balanceOf[0x290a76806ec39e731877b8874a32761d60321bcd] = totalSupply;
        Transfer(address(0), 0x290a76806ec39e731877b8874a32761d60321bcd, totalSupply);
    }
}
