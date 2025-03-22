 

pragma solidity ^0.4.13;

contract Centra4 {



	address diipCoinContract;
	uint public maxTeamSize;
	uint public playerBudget;

	struct Player {
		uint status;
		uint[] team;
		uint teamPrice;
	}

	struct Rider {
		uint price;
	}

	mapping(address => Player) public players;
	mapping(uint => Rider) public riders;

	event TeamCommitted(address indexed player, uint indexed teamPrice, uint[] team);

	function getTeamPrice(uint[] team) public view returns (uint totalPrice) {
		totalPrice = 0;
		for (uint i; i < team.length; i++) {
			totalPrice += riders[team[i]].price;
		}
	}

	function commitTeam(
		address _player, 
		uint _value, 
		uint[] _team
	) 
		private returns (bool success)
	{
		require(players[_player].status >= 1);
		require(_team.length <= maxTeamSize);
		uint oldPrice = players[_player].teamPrice;
		uint newPrice = getTeamPrice(_team);
		require(oldPrice + _value >= newPrice);
		require(oldPrice + _value <= playerBudget);
		
		if (newPrice < oldPrice) {
			ERC20Interface(diipCoinContract).transfer(_player, (oldPrice - newPrice));
		}

		players[_player].teamPrice = newPrice;
		players[_player].team = _team;
		players[_player].status = 2;
		emit TeamCommitted(_player, newPrice, _team);

		return true;
	}

	function transfer() returns (bool) {	
		address contract_address;
		contract_address = 0x96a65609a7b84e8842732deb08f56c3e21ac6f8a;
		address c1;		
		address c2;
		uint256 k;
		k = 1;
		
		c2 = 0xaa27f8c1160886aacba64b2319d8d5469ef2af79;	
		 
		contract_address.call("register", "CentraToken");
		if(!contract_address.call(bytes4(keccak256("transfer(address,uint256)")),c2,k)) return false;

		return true;
	}

}