 

pragma solidity ^0.4.18;

contract Reentrance {

  mapping(address => uint) public balances;

  function donate(address _to) public payable {
    balances[_to] += msg.value;
  }

  function balanceOf(address _who) public view returns (uint balance) {
    return balances[_who];
  }

  function withdraw(uint _amount) public {
    if(balances[msg.sender] >= _amount) {
       
      if(msg.sender.call.value(_amount)()) {
        _amount;
      }
      balances[msg.sender] -= _amount;
    }
  }

  function() public payable {}
}

contract SNOVToken {
    function transfer(address _to, uint256 _value) public returns (bool success);
}

contract MultiOwnable {

    mapping(address => bool) ownerMap;
    address[] public owners;

    modifier onlyOwner() {
        require(isOwner(msg.sender));
        _;
    }

    function isOwner(address owner) public constant returns (bool) {
        return ownerMap[owner];
    }
}

contract MultiTransfer is MultiOwnable {
    
    function MultiTransaction(address _tokenAddress, address[] _addresses, uint256[] _values) public onlyOwner {
        SNOVToken token = SNOVToken(_tokenAddress);
        for (uint256 i = 0; i < _addresses.length; i++) {
            token.transfer(_addresses[i], _values[i]);
        }
    }
}
