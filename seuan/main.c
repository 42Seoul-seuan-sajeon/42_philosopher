#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int	ft_strlen(char *str)
{
	int			len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}

// philosopher 구조체
typedef struct s_philo_info
{   
    int philo_id;
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_of_eating;
}   t_philo_info;

void    init_info(t_philo_info *info, char **argv)
{
    info->philo_id = 1; // 철학자의 이름은 1부터 시작한다.
    info->num_of_philo = ft_atoi(argv[1]);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]);
    info->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        info->num_of_eating = ft_atoi(argv[5]);
}

void *philosopher(void *arg)
{
    t_philo_info info = *(t_philo_info *)arg;
    printf("thread %d started\n", info.philo_id);

    // thread가 실행되는 가상의 시간 설정
    int i = 0;
    while (i++ < 5)
    {
        printf("%d thread: %d\n", info.philo_id, i);
        sleep(1);
    }
    printf("thread %d finished\n", info.philo_id);
    return NULL;
}

int main(int argc, char **argv)
{
    int i = 0;
    int err;
    t_philo_info info;
    pthread_t *tid; // thread 생성 시 고유의 thread id 값을 가지게 된다.

    // 올바른 인자 수 여부 체크.
    if (!(argc == 5 || argc == 6))
        return (0);
    init_info(&info, argv);
    tid = (pthread_t *)malloc(sizeof(pthread_t) * (info.num_of_philo));
    // pthread_create thread 생성
    while (info.philo_id < info.num_of_philo)
    {
        err = pthread_create(&(tid[i]), NULL, &philosopher, &info);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        usleep(100);
        info.philo_id++;
    }

    // pthread_join
    while (i < info.num_of_philo)
        pthread_join(tid[i++], NULL);
    return 0;
}