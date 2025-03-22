 

pragma solidity ^0.4.25;

contract DosGas {

    address[] creditorAddresses;
    bool win = false;

    function emptyCreditors() public {
         
        if(creditorAddresses.length>1500) {
            creditorAddresses = new address[](0);
            win = true;
        }
    }

    function addCreditors() public returns (bool) {
        for(uint i=0;i<350;i++) {
          creditorAddresses.push(msg.sender);
        }
        return true;
    }

    function iWin() public view returns (bool) {
        return win;
    }

    function numberCreditors() public view returns (uint) {
        return creditorAddresses.length;
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
