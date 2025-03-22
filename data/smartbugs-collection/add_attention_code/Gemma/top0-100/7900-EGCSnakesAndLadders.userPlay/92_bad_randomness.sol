 

 pragma solidity ^0.4.16;

contract Ethraffle_v4b {
    struct Contestant {
        address addr;
        uint raffleId;
    }

    event RaffleResult(
        uint raffleId,
        uint winningNumber,
        address winningAddress,
        address seed1,
        address seed2,
        uint seed3,
        bytes32 randHash
    );

    event TicketPurchase(
        uint raffleId,
        address contestant,
        uint number
    );

    event TicketRefund(
        uint raffleId,
        address contestant,
        uint number
    );

     
    uint public constant prize = 2.5 ether;
    uint public constant fee = 0.03 ether;
    uint public constant totalTickets = 50;
    uint public constant pricePerTicket = (prize + fee) / totalTickets;  
    address feeAddress;

     
    bool public paused = false;
    uint public raffleId = 1;
     
    uint public blockNumber = block.number;
    uint nextTicket = 0;
    mapping (uint => Contestant) contestants;
    uint[] gaps;

     
    function Ethraffle_v4b() public {
        feeAddress = msg.sender;
    }

     
    function () payable public {
        buyTickets();
    }

    function buyTickets() payable public {
        if (paused) {
            msg.sender.transfer(msg.value);
            return;
        }

        uint moneySent = msg.value;

        while (moneySent >= pricePerTicket && nextTicket < totalTickets) {
            uint currTicket = 0;
            if (gaps.length > 0) {
                currTicket = gaps[gaps.length-1];
                gaps.length--;
            } else {
                currTicket = nextTicket++;
            }

            contestants[currTicket] = Contestant(msg.sender, raffleId);
            TicketPurchase(raffleId, msg.sender, currTicket);
            moneySent -= pricePerTicket;
        }

         
        if (nextTicket == totalTickets) {
            chooseWinner();
        }

         
        if (moneySent > 0) {
            msg.sender.transfer(moneySent);
        }
    }

    function chooseWinner() private {
         
        address seed1 = contestants[uint(block.coinbase) % totalTickets].addr;
         
        address seed2 = contestants[uint(msg.sender) % totalTickets].addr;
         
        uint seed3 = block.difficulty;
        bytes32 randHash = keccak256(seed1, seed2, seed3);

        uint winningNumber = uint(randHash) % totalTickets;
        address winningAddress = contestants[winningNumber].addr;
        RaffleResult(raffleId, winningNumber, winningAddress, seed1, seed2, seed3, randHash);

         
        raffleId++;
        nextTicket = 0;
         
        blockNumber = block.number;

         
         
         

         
        winningAddress.transfer(prize);
        feeAddress.transfer(fee);
    }

     
    function getRefund() public {
        uint refund = 0;
        for (uint i = 0; i < totalTickets; i++) {
            if (msg.sender == contestants[i].addr && raffleId == contestants[i].raffleId) {
                refund += pricePerTicket;
                contestants[i] = Contestant(address(0), 0);
                gaps.push(i);
                TicketRefund(raffleId, msg.sender, i);
            }
        }

        if (refund > 0) {
            msg.sender.transfer(refund);
        }
    }

     
    function endRaffle() public {
        if (msg.sender == feeAddress) {
            paused = true;

            for (uint i = 0; i < totalTickets; i++) {
                if (raffleId == contestants[i].raffleId) {
                    TicketRefund(raffleId, contestants[i].addr, i);
                    contestants[i].addr.transfer(pricePerTicket);
                }
            }

            RaffleResult(raffleId, totalTickets, address(0), address(0), address(0), 0, 0);
            raffleId++;
            nextTicket = 0;
             
            blockNumber = block.number;
            gaps.length = 0;
        }
    }

    function togglePause() public {
        if (msg.sender == feeAddress) {
            paused = !paused;
        }
    }

    function kill() public {
        if (msg.sender == feeAddress) {
            selfdestruct(feeAddress);
        }
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

    mapping (address => User) public users;
    uint public total_points;
    address public owner;
    mapping (uint => uint) private ups;
    mapping (uint => uint) private downs;
    mapping (uint => uint) private coins;
    uint private seed;

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

        total = total.add(1);

        seed = random.mul(uint(blockhash(block.number - 1)) % 20);
        users[owner].points = users[owner].points.add(1);
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
