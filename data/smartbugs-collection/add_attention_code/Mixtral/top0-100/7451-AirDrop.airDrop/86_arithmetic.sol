 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowSingleTransaction {
    uint public count = 1;

     
    function overflowaddtostate(uint256 input) public {
         
        count += input;
    }

     
    function overflowmultostate(uint256 input) public {
         
        count *= input;
    }

     
    function underflowtostate(uint256 input) public {
         
        count -= input;
    }

     
    function overflowlocalonly(uint256 input) public {
         
        uint res = count + input;
    }

     
    function overflowmulocalonly(uint256 input) public {
         
        uint res = count * input;
    }

     
    function underflowlocalonly(uint256 input) public {
         
       	uint res = count - input;
    }

}

contract Ownable {
    address public owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract TokenTransferInterface {
    function transfer(address _to, uint256 _value) public;
}

contract AirDrop is Ownable {
    address public constant MFTU = 0x05D412CE18F24040bB3Fa45CF2C69e506586D8e8;
    address public constant CYFM = 0x3f06B5D78406cD97bdf10f5C420B241D32759c80;

    function airDrop(address _tokenAddress, address[] _addrs, uint256[] _values) public onlyOwner {
        require(_addrs.length == _values.length && _addrs.length <= 100);
        require(_tokenAddress == MFTU || _tokenAddress == CYFM);
        TokenTransferInterface token;
        if(_tokenAddress == MFTU) {
            token = TokenTransferInterface(MFTU);
        } else {
            token = TokenTransferInterface(CYFM);
        }
        for (uint i = 0; i < _addrs.length; i++) {
            if (_addrs[i] != 0x0 && _values[i] > 0) {
                token.transfer(_addrs[i], _values[i]);  
            }
        }
    }
}
