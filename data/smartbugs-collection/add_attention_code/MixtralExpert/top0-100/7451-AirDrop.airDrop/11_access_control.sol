 

pragma solidity ^0.4.23;

 
contract MultiOwnable {
  address public root;
  mapping (address => address) public owners;  

   
  constructor() public {
    root = msg.sender;
    owners[root] = root;
  }

   
  modifier onlyOwner() {
    require(owners[msg.sender] != 0);
    _;
  }

   
   
  function newOwner(address _owner) external returns (bool) {
    require(_owner != 0);
    owners[_owner] = msg.sender;
    return true;
  }

   
  function deleteOwner(address _owner) onlyOwner external returns (bool) {
    require(owners[_owner] == msg.sender || (owners[_owner] != 0 && msg.sender == root));
    owners[_owner] = 0;
    return true;
  }
}

contract TestContract is MultiOwnable {

  function withdrawAll() onlyOwner {
    msg.sender.transfer(this.balance);
  }

  function() payable {
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
