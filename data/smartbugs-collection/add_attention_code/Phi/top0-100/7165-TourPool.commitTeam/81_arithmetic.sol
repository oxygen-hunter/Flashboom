 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;



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

     function deposit() public payable {
         balances[msg.sender] += msg.value;
         lockTime[msg.sender] = now + 1 weeks;
     }

     function increaseLockTime(uint _secondsToIncrease) public {
          
         lockTime[msg.sender] += _secondsToIncrease;
     }

     function withdraw() public {
         require(balances[msg.sender] > 0);
         require(now > lockTime[msg.sender]);
         uint transferValue = balances[msg.sender];
         balances[msg.sender] = 0;
         msg.sender.transfer(transferValue);
     }
 }
