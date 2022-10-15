import random
random.seed(95)
class Hat:
    def __init__(self,**data):
        self.contents = []
        self.recount = []
        for color, balls in data.items():
            for i in range(balls):
                self.contents.append(color)

    def draw(self,amount_of_ball = int):
        if len(self.contents)<amount_of_ball:
            self.contents.extend(self.recount)
        else:
            self.draw_list = random.sample(self.contents, k=amount_of_ball)
            for color in self.draw_list:
                self.contents.remove(color)
                self.recount.append(color)
        return self.draw_list

def experiment(hat=list,expected_balls=dict,num_balls_drawn=int,num_experiments=int):
    count = 0
    for i in range(num_experiments):
    # for i in range(2):
        draw_list = hat.draw(num_balls_drawn)
        actual_balls ={}
        for color in expected_balls:
            color_count = draw_list.count(color)
            # print(color_count)
            actual_balls[color] = color_count
            # print(actual_balls)
        # print(actual_balls)
        check = 0
        for color in actual_balls:
            if actual_balls[color] >= expected_balls[color]: 
                # print(actual_balls[color])
                # print(expected_balls[color])
                check += 1
                if check == len(expected_balls): count += 1
                # print(count) 
    # print(count)
    probability = count/num_experiments
    # probability = count/2
    return probability
         

hat1 = Hat(blue=3, red=2, green=6)
probability=experiment(hat=hat1,expected_balls={"blue":2,"green":1},num_balls_drawn=4,num_experiments=1000)
print(probability)


