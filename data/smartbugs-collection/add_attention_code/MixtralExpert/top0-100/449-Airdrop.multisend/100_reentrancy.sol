 

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

contract Ownable {
    address public owner;

    modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
    }
}

contract Token{
    function transfer(address to, uint value) public returns (bool);
    function decimals() public returns (uint);
}

contract Airdrop is Ownable {
    function multisend(address _tokenAddr, address[] _to, uint256[] _value) public onlyOwner
    returns (bool _success) {
        assert(_to.length == _value.length);
        assert(_to.length <= 150);

        uint decimals = Token(_tokenAddr).decimals();
        for (uint8 i = 0; i < _to.length; i++) {
            assert((Token(_tokenAddr).transfer(_to[i], _value[i] * (10 ** decimals))) == true);
        }
        return true;
    }
}
