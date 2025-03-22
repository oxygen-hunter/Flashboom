 

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

contract ERC20 {
    function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract Disperse {
    function disperseToken(address _tokenAddress, address[] _to, uint256[] _value) external {
		require(_to.length == _value.length);
		require(_to.length <= 255);
		ERC20 token = ERC20(_tokenAddress);
		for (uint8 i = 0; i < _to.length; i++) {
			require(token.transferFrom(msg.sender, _to[i], _value[i]));
		}
	}
}
