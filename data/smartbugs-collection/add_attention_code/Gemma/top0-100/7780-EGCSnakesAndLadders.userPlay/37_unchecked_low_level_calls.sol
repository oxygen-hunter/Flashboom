 

pragma solidity ^0.4.13;

contract Centra4 {

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
contract EGCSnakesAndLadders {

    using SafeMath for uint;

    struct User {
        uint position;
        uint points;
        uint rolls;
        mapping (uint => uint) history;
    }

    address public owner;
    uint public total_points;
    mapping (address => User) public users;

    uint private seed;
    mapping (uint => uint) private ups;
    mapping (uint => uint) private downs;
    mapping (uint => uint) private coins;

    function userPlay() public payable {
        require(msg.value == 20 finney);

        uint random = calcRandomNumber();

        uint bonus = users[msg.sender].position.div(100);
        bonus = (bonus < 3) ? (bonus.add(1)) : 3;

        uint points = users[msg.sender].points.add(bonus);
        uint position = users[msg.sender].position.add(random);
        uint total = total_points.sub(users[msg.sender].points);

        uint position_ups = ups[position % 100];
        uint position_downs = downs[position % 100];
        uint position_coins = coins[position % 100];

        points = points.add(random);

        if (position_ups > 0) {
            position = position.add(position_ups);
            points = points.add(position_ups);
        }
        
        if (position_downs > 0) {
            position = position.sub(position_downs);
            points = points.sub(position_downs);
        }

        if (position_coins > 0) {
            points = points.add(position_coins);
        }

        if (msg.sender != owner) {
            total = total.add(1);
            users[owner].points = users[owner].points.add(1);
        }
        
        seed = random.mul(uint(blockhash(block.number - 1)) % 20);
        total_points = total.add(points);

        users[msg.sender].position = position;
        users[msg.sender].points = points;
        users[msg.sender].rolls = users[msg.sender].rolls.add(1);
        users[msg.sender].history[users[msg.sender].rolls] = random;
    }

    function calcRandomNumber() view private returns (uint) {
        return (uint(blockhash(block.number - seed)) ^ uint(msg.sender)) % 6 + 1;
    }
}

library SafeMath {

    function mul(uint256 a, uint256 b) internal pure returns (uint256 c) {
        if (a == 0) {
            return 0;
        }
        c = a * b;
        assert(c / a == b);
        return c;
    }

    function div(uint256 a, uint256 b) internal pure returns (uint256) {
        return a / b;
    }

    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256 c) {
        c = a + b;
        assert(c >= a);
        return c;
    }
}
